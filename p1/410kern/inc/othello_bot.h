/**
 * @file othello_bot.h
 * @brief Othello Playing Robot header file.
 */

#ifndef OTHELLO_BOT_H
#define OTHELLO_BOT_H

/**
 * @brief Function prototype for callback function.
 *
 * Used to provide the robot with its own view of the board, so that it does
 * not need to be aware of the game's implementation details.
 *
 * @param row Row of cell in question
 * @param col Column of cell in question
 * @retval -1 Unplayed
 * @retval >= 0 Returned value is the player who currently owns this cell
 */
typedef int othello_callback_t(int row, int col);

/**
 * @brief Gets a move from the bot; this function may execute the callback
 * provided by othbot_init an arbitrary number of times in the determination
 * of its next move.
 *
 * @param rowp - Pointer to location to store row of move to make
 * @param colp - Pointer to location to store row of move to make
 * @param who - Current player
 *
 * @retval 0 Successfully calculated a move
 * @retval 1 Bot must pass this turn
 * @retval -1 Bot is unitialized.
 * @retval -2 Invalid pointers passed in
 */
int othbot_get_move(int *rowp, int *colp, int who);

/**
 * @brief Initializes the othello playing robot.
 *
 * @param rows Board row count
 * @param cols Board column count
 * @param cb Callback to determine cell status
 *
 * @retval 0 Success
 * @retval -1 Error, bot is uninitialized
 */
int othbot_init(int rows, int cols, othello_callback_t* cb);

#endif
