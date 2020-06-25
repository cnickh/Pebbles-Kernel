/**
 * @file othello_bot.c
 * @brief Othello Playing Robot.  Not very clever, but hopefully not
 * too simple either.
 */

#include <rand.h>
#include <string.h>
#include <malloc.h>
#include "othello_bot.h"

#include <stdio.h>
#include <kerndebug.h>

	/** A list of directions for moving.
	 *
	 * @invariant Directions are diametrically opposite if
	 * all three bits differ.
	 */
enum direction {
	DIR_NORTH = 0x0,
	DIR_NORTHEAST = 0x1,
	DIR_EAST = 0x2,
	DIR_SOUTHEAST = 0x3,
	DIR_NORTHWEST = 0x4,
	DIR_WEST = 0x5,
	DIR_SOUTHWEST = 0x6,
	DIR_SOUTH = 0x7,
	DIR_COUNT = 0x8
};

	/** initialization status of the bot.  1 if so, 0 if not. */
static int othbot_inited = 0;
	/** board size as a cache to avoid multiplications */
static int othbot_board_size = 0;
	/** board row count as provided by othbot_init */
static int othbot_board_rows = 0;
	/** board column count as provided by othbot_init */
static int othbot_board_cols = 0;
	/** callback function as provided by othbot_init */
static othello_callback_t *othbot_callback = NULL;
	/** list of numbers relatively prime to and less than
	 * 	othbot_board_size. ;)
	 */
static int *othbot_relprimes = NULL;
	/** number of numbers in othbot_relprimes */
static int othbot_relprimes_num = 0;

/**
 * @brief Determine if parameters are relatively prime.
 *
 * Core stolen from
 * http://en.wikipedia.org/wiki/Binary_GCD_algorithm#Implementation_in_C
 */
static int othbot_coprime( int i, int j )
{
	if ( i == 0 || j == 0 )
		return 0;

	/* Quick check for shared factor of two */
	if ( ((i & 0x1) == 0) && ((j & 0x1) == 0) )
		return 0;

	do
	{
		if ( (i & 0x1) == 0 )
			i >>= 1;
		else if ( (j & 0x1) == 0)
			j >>= 1;
		else if ( i >= j )
			i = (i - j) >> 1;
		else
			j = (j - i) >> 1;
	} while( i > 0 );

	if ( j == 1 )
		return 1;

	return 0;
}

/** @brief Utility function to make moves if possible, updating a pointer and
  * row/column indices as necessary
	*
	* @return The array delta to the new cell, or 0 if no move is possible
  */
static int
othbot_utility_move( enum direction d, int *r, int *c )
{
  switch ( d )
  {
    case DIR_NORTH:
      if ( 0 == *r )
      {
        return 0;
      }
      *r -= 1;
      return -othbot_board_cols;
    case DIR_SOUTH:
      if ( othbot_board_rows - 1 == *r )
      {
        return 0;
      }
      *r += 1;
      return +othbot_board_cols;
    case DIR_EAST:
      if ( othbot_board_cols - 1 == *c)
      {
        return 0;
      }
      *c += 1;
      return +1;
    case DIR_WEST:
      if ( 0 == *c )
      {
        return 0;
      }
      *c -= 1;
      return -1;
    case DIR_NORTHEAST:
      if ( (0 == *r) || (othbot_board_cols - 1 == *c) )
      {
        return 0;
      }
      *c += 1;
      *r -= 1;
      return 1-othbot_board_cols;
    case DIR_SOUTHEAST:
      if ( (othbot_board_cols - 1 == *c) || (othbot_board_rows - 1 == *r) )
      {
        return 0;
      }
      *c += 1;
      *r += 1;
      return 1+othbot_board_cols;
    case DIR_SOUTHWEST:
      if ( (0 == *c) || (othbot_board_rows - 1 == *r) )
      {
        return 0;
      }
      *c -= 1;
      *r += 1;
      return othbot_board_cols - 1;
    case DIR_NORTHWEST:
      if ( (0 == *c) || (0 == *r) )
      {
        return 0;
      }
      *c -= 1;
      *r -= 1;
      return -othbot_board_cols - 1;
    default:
      return 0;
  }
}

/** @brief A simple function to determine if a cell is playable. */
static int othbot_is_playable(int row, int col, int who)
{
	enum direction dir = DIR_NORTH;
	int recr, recc; 

	recc = col;
	recr = row;

	/* lprintf(" Considering %d %d", recr, recc); */

	/* Fast bailout on already played */
	if ( othbot_callback(recr, recc) != -1 )
	{
		return 0;
	}

	while( recc != col || recr != row || dir != DIR_COUNT )
	{
		int steps = 0, status, delta;
		do {
			delta = othbot_utility_move(dir, &recr, &recc);
			status = othbot_callback(recr, recc);
			steps++;
		} while ( delta != 0 && status >= 0 && status != who );

		if ( steps > 1 && status >= 0 && status == who )
		{
			/* lprintf(" is playable : delta %d cell %d %d", delta, recr, recc); */
			return 1;
		}

		/* Increment direction and return to base */
		dir++;
		recc = col;
		recr = row;
	}

	return 0;
}

int othbot_get_move( int *rowp, int *colp, int who )
{
	int stride, init_cell, cell, row, col;

	if (rowp == NULL)
		return -2;
	if (colp == NULL)
		return -2;
	
	if (othbot_inited == 0)
		return -1;

	stride = othbot_relprimes[genrand() % othbot_relprimes_num];
	cell = init_cell = genrand() % othbot_board_size;

	/* lprintf("OTHBOT STRIDE %d FROM %d", stride, init_cell); */

	do
	{
		col = cell % othbot_board_cols;
		row = cell / othbot_board_cols;

		if (othbot_is_playable(row,col,who) == 1)
		{
			/* lprintf("OTHBOT MAKING MOVE AT %d %d", row, col); */
			*rowp = row;
			*colp = col;
			return 0;
		} else {
			/* lprintf(" OTHBOT GOT NOT PLAYABLE AT %d %d", row, col); */
		}

		cell = (cell + stride) % othbot_board_size;
	} while (cell != init_cell);

	/* lprintf("OTHBOT PASSING!"); */

	/* No moves, we must pass */
	return 1;
}

int othbot_init( int rows, int cols, othello_callback_t* cb)
{
	int i;

	othbot_callback = cb;
	othbot_board_rows = rows;
	othbot_board_cols = cols;
	othbot_board_size = rows * cols;

	/* Start with a reasonable size */
	int rp_size = 10;

	if ( othbot_relprimes != NULL )
	{
		othbot_relprimes = realloc(othbot_relprimes, rp_size*sizeof(int));
	}
	else
	{
		othbot_relprimes = malloc(rp_size*sizeof(int));
	}
	othbot_relprimes_num = 0;

	for (i = 0; i < othbot_board_size; i++)
	{
		if ( othbot_coprime(i, othbot_board_size) == 1 )
		{
			if ( othbot_relprimes_num == rp_size )
			{
				/* Grow our array */
				rp_size *= 2;
				othbot_relprimes = realloc(othbot_relprimes, rp_size*sizeof(int));
			}

			othbot_relprimes[othbot_relprimes_num] = i;
			othbot_relprimes_num++;
		}
	}

	if ( othbot_relprimes_num > 0 )
	{
		othbot_inited = 1;
		return 0;
	}

	othbot_inited = 0;
	return -1;
}
