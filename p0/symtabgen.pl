#!/usr/local/bin/perl5

#
# This program was written for use in 15-410 Spring 04
#
# This program presumes that there is a global variable
# called functions and that it is an array of functsym_t
# in the executable on which it is called. It fills in this
# array with information from the stabs.
#
# by Michael Ashley-Rollman (mpa)
#

use strict;
use Fcntl;
use IO::File;

my $verbose = 0;     # Prints out a bunch of information about what it finds

my $prog;

$prog = $0;
$prog =~ s/^.*\///;

my @types = ("unknown", "int", "char", "float", "double", "char *", "char **");
my @typepatterns = ("", "^p\\(0,1\\)", "\\(0,2\\)", "^p\\(0,12\\)", "^p\\(0,13\\)", "^p\\((\\d*,\\d*)\\)=\\*\\(0,2\\)", "^p\\((\\d*,\\d*)\\)=\\*\\(0,19\\)");

my @symbols;
my $symbol;
my $i;

die "usage: $prog <program name>\n" unless $#ARGV == 0;
my $filename = $ARGV[0];

@symbols = `objdump -G $filename`;

my $file = &open_file_at_functions($filename);
my $temp;

$temp = sysseek($file, 0, &SEEK_CUR);

#arguments that are read from executable
my $max_num_args;
my $max_num_functions;
my $sizeof_argsym;
my $sizeof_functsym;
my $max_arg_name;
my $max_fun_name;

#read sizeof functsym_t
sysread($file, $sizeof_functsym, 4);
$sizeof_functsym = unpack("I", $sizeof_functsym);

print "sizeof_functsym = $sizeof_functsym\n" if $verbose;

#read max number of functions
sysread($file, $max_num_functions, 2);

$max_num_functions = unpack("S", $max_num_functions);

print "max_num_functions = $max_num_functions\n" if $verbose;

#read max number of arguments
sysread($file, $max_num_args, 1);
$max_num_args = unpack("C", $max_num_args);

print "max_num_args = $max_num_args\n" if $verbose;

#read sizeof argsym_t
sysread($file, $sizeof_argsym, 1);
$sizeof_argsym = unpack("C", $sizeof_argsym);

print "sizeof_argsym = $sizeof_argsym\n" if $verbose;

#read maximum length of function names
sysread($file, $max_fun_name, 1);
$max_fun_name = unpack("C", $max_fun_name);

print "max_fun_name = $max_fun_name\n" if $verbose;

#read maximum length of argument names
sysread($file, $max_arg_name, 1);
$max_arg_name = unpack("C", $max_arg_name);

print "max_arg_name = $max_arg_name\n" if $verbose;

sysseek($file, $temp, &SEEK_SET);

my $num_args = $max_num_args;
my $num_functions = 0;
my @functions;
my $curfunct;
my $fixed_stringarray = 0;
my $fixed_string = 0;

foreach $symbol (@symbols) {
  my $addr;
  my $name;
  my $type;
  my $typepat;
  my $typematch;
  my $newtype;
  my @supername;
  my @info;

  @info = split (/ +/,$symbol);

  $addr = @info[4];
  @supername = split(/:/,@info[6]);
  $name = @supername[0];
  $typepat = substr(@info[6], length($name) + 1);

  $temp = substr(@typepatterns[5], 2);

  if ($fixed_string != 1 &&
      $typepat =~ /$temp/) {

      $typematch = "^p\\($1\\)\$";

      @typepatterns[5] = $typematch;

      @typepatterns[6] = "^p\\((\\d*,\\d*)\\)=\\*\\($1\\)";

      $fixed_string = 1;
  }

  for ($i = 0; $i <= $#types; $i++) {
    $typematch = @typepatterns[$i];
    $newtype = @types[$i];

    $temp = substr($typematch, 2);

    if ($typepat =~ /$typematch/) {
      $temp = $1;

      $type = $newtype;


      unless ($fixed_stringarray || $type !~ /^char \*\*$/) {
	$fixed_stringarray = 1;

	$typematch = "\\($temp\\)\$";

	@typepatterns[$i] = $typematch;
      }
    }
    elsif ($fixed_stringarray != 1 &&
	   $newtype =~ /^char \*\*$/ &&
	   $typepat =~ /$temp/) {
      $fixed_stringarray = 1;

      $typematch = "\\($1\\)\$";

      @typepatterns[$i] = $typematch;
    }
  }

  if (@info[1] =~ "FUN") {
    print "function $name at $addr\n" if $verbose;

    if ($num_functions >= $max_num_functions) {
      print "warning: too many functions";
      print "         ignoring $name at 0x$addr\n";
    }
    else {
      if ($num_functions >= 1) {
	@functions[$num_functions - 1] = $curfunct;
      }

      # zero out current function
      for ($i = 0; $i < $sizeof_functsym + 8; $i++) {
	substr($curfunct, $i, 1) = pack("c", "0");
      }

      # write the address for the function
      substr($curfunct,0,8) = $addr;

      $temp = $addr;
      substr($addr,0,2) = substr($temp,6,2);
      substr($addr,2,2) = substr($temp,4,2);
      substr($addr,4,2) = substr($temp,2,2);
      substr($addr,6,2) = substr($temp,0,2);

      $addr = pack("H8", $addr);

      substr($curfunct, 8, 4) = $addr;

      if (length($name) >= $max_fun_name) {
	$temp = $max_fun_name;
      }
      else {
	$temp = length($name);
      }
      substr($curfunct, 12, $temp) = substr($name,0,$temp);

      $num_args = 0;
      $num_functions ++;
    }
  }
  elsif (@info[1] =~ "PSYM") {
    print "\targument $name at offset $addr has type $type\n" if $verbose;
    if ($num_args == $max_num_args) {
      print "warning: function has more than $max_num_args arguments\n";
      print "         ignoring additional arguments\n";
    }
    else {
      if ($type =~ /^char$/) { $temp = 0; }
      elsif ($type =~ /^int$/) { $temp = 1; }
      elsif ($type =~ /^float$/) { $temp = 2; }
      elsif ($type =~ /^double$/) { $temp = 3; }
      elsif ($type =~ /^char \*$/) { $temp = 4; }
      elsif ($type =~ /^char \*\*$/) { $temp = 5; }
      else { $temp = -1; }

      my $arg_start = 8 + 4 + $max_fun_name + $sizeof_argsym * $num_args;

      # write the type of  the argument
      $temp = pack("i",$temp);
      substr($curfunct, $arg_start, 4) = $temp;

      $temp = $addr;
      # write the offset of the argument
      substr($addr,0,2) = substr($temp,6,2);
      substr($addr,2,2) = substr($temp,4,2);
      substr($addr,4,2) = substr($temp,2,2);
      substr($addr,6,2) = substr($temp,0,2);

      $addr = pack("H8",$addr);
      substr($curfunct, $arg_start + 4, 4) = $addr;

      if (length($name) >= $max_arg_name) {
	$temp = $max_arg_name;
      }
      else {
	$temp = length($name);
      }
      substr($curfunct, $arg_start + 8, $temp) = substr($name,0,$temp);

      $num_args++;
    }
  }
  elsif (@info[1] =~ "LSYM") {
    if ($type =~ /char/) {

      $temp = 0;

      #check to see if current function has a variable with the same name
      #of type int

      my $arg_start = 8 + 4 + $max_fun_name;

      for ($i = 0; $i < $num_args; $i++, $arg_start += $sizeof_argsym) {
	# get the type
	$temp = substr($curfunct, $arg_start, 4);
	$temp = unpack("i", $temp);

	# truncate name
	if (length ($name > $max_arg_name)) {
	  $name = substr($name, 0, $max_arg_name);
	}

	# if the arg is an int and has the same name
	if ($temp == 1 &&
	    substr($curfunct,
		   $arg_start + 8,
		   length ($name)) =~ "$name" &&
	    (length($name) == $max_arg_name ||
	     substr($curfunct,
		   $arg_start + 8 + length($name),
		   1) =~ "\0")) {
	  # set the new type
	  $temp = pack("i", $type);
	  substr($curfunct, $arg_start, 4) = $temp;

	  # set the new offset from esp
	  $temp = $addr;

	  substr($addr,0,2) = substr($temp,6,2);
	  substr($addr,2,2) = substr($temp,4,2);
	  substr($addr,4,2) = substr($temp,2,2);
	  substr($addr,6,2) = substr($temp,0,2);

	  $addr = pack("H8",$addr);
	  substr($curfunct, $arg_start + 4, 4) = $addr;
	}
      }
    }
  }
  else {

  }
}

@functions[$num_functions - 1] = $curfunct;

@symbols = `objdump -t $filename`;

foreach $symbol (@symbols) {
  my @info;
  my $name;
  my $addr;
  my $function;

  @info = split (/ +/,$symbol);

  if (@info[2] =~ /F/) {
    $addr = @info[0];
    if (@info[5] =~ /.+/) {
      $name = @info[5];
    }
    else {
      $name = @info[4];
    }

    chomp ($name);
    if (function_not_exists($addr, \@functions)) {
      if ($num_functions >= $max_num_functions) {
	      print "warning: too many functions";
	      print "         ignoring $name at 0x$addr\n";
      }
      else {

	print "function $name at 0x$addr\n" if $verbose;

	# zero out current function
	for ($i = 0; $i < $sizeof_functsym + 8; $i++) {
	  substr($curfunct, $i, 1) = pack("c", "0");
	}

	substr($curfunct, 0, 8) = $addr;

	$temp = $addr;
	# write the offset of the argument
	substr($addr,0,2) = substr($temp,6,2);
	substr($addr,2,2) = substr($temp,4,2);
	substr($addr,4,2) = substr($temp,2,2);
	substr($addr,6,2) = substr($temp,0,2);

	$addr = pack("H8",$addr);
	substr($curfunct, 8, 4) = $addr;

	$name = substr($name, 0, $max_fun_name);
	substr($curfunct, 8 + 4, length($name)) = $name;

	@functions[$num_functions] = $curfunct;
	$num_functions++;
      }
    }
  }
}

@functions = sort(@functions);

if ($num_functions < $max_num_functions) {

  # zero out current function
  for ($i = 0; $i < $sizeof_functsym + 8; $i++) {
    substr($curfunct, $i, 1) = pack("c", "0");
  }

  #null terminate the list
  @functions[$num_functions] = $curfunct;
}

foreach $curfunct (@functions) {
  my $temp = substr($curfunct, 0,8);
  syswrite($file, $curfunct, $sizeof_functsym, 8);
}

sub function_not_exists {
  my $funref = $_[1];
  my @functions = @$funref;
  my $addr = $_[0];
  my $function;

  foreach $function (@functions) {
    if (substr($function, 0, 8) =~ /^$addr$/){
      return 0;
    }
  }
  return 1;
}

sub open_file_at_functions {
  my $fname = $_[0];
  my $handle = new IO::File;

  my $shoff;
  my $shentsize;
  my $shstrndx;
  my $shstrtaboff;
  my $strtaboff;
  my $symtaboff;
  my $functssect;
  my $functsoff;
  my $functssectoff;
  my $i;
  my $temp;

  open ($handle, "+<$fname") || die "$prog: cannot read $fname: $!";

  # sysseek to e_shoff in the ELF Header
  sysseek($handle, 32, &SEEK_SET);

  (sysread($handle, $shoff , 4) == 4) || die "$prog: error reading $fname: $!";
  $shoff = unpack("I", $shoff);

  # sysseek to  e_shentsize in the ELF Header
  sysseek($handle, 46, &SEEK_SET);

  (sysread($handle, $shentsize, 2) == 2)  || die "$prog: error reading $fname: $!";
  $shentsize = unpack("S", $shentsize);

  # sysseek to e_shstrndx in the ELF Header
  sysseek($handle, 50, &SEEK_SET);

  (sysread($handle, $shstrndx, 2) == 2)  || die "$prog: error reading $fname: $!";
  $shstrndx = unpack("S", $shstrndx);

  # sysseek to the string table offset in the string table section header
  sysseek($handle, $shoff + $shstrndx * $shentsize + 16, &SEEK_SET);

  (sysread($handle, $shstrtaboff, 4) == 4) || die "$prog: error reading $fname: $!";
  $shstrtaboff = unpack("I", $shstrtaboff);


  # find the symbol table
  $i = 0;
  $symtaboff = "";
  while($symtaboff !~ /.+/ || $strtaboff !~ /.+/) {
    # sysseek to the i-th section
    sysseek($handle, $shoff + $i * $shentsize, &SEEK_SET);

    (sysread($handle, $temp, 4) == 4) || die "$prog: error reading $fname: $!";
    $temp = unpack("I", $temp);

    # look up the name in the string table and see if it's .symtab

    sysseek($handle, $shstrtaboff + $temp, &SEEK_SET);

    (sysread($handle, $temp, 7) == 7) || die "$prog: error reading $fname: $!";

    # If we finally found the symbol table
    if ($temp =~ /\.symtab/) {
      # sysseek to the section offset for the symbol table
      sysseek($handle, $shoff + $i * $shentsize + 16, &SEEK_SET);

      (sysread($handle, $symtaboff, 4) == 4) || die "$prog: error reading $fname: $!";
      $symtaboff = unpack("I", $symtaboff);
    }
    # If we finally found the string table
    if ($temp =~ /\.strtab/) {
      #sysseek to the section offset for the string table
      sysseek($handle, $shoff + $i * $shentsize + 16, &SEEK_SET);

      (sysread($handle, $strtaboff, 4) == 4) || die "$prog: error reading $fname: $!";
      $strtaboff = unpack("I", $strtaboff);
    }
    $i++;
  }

  # find the variable we're looking for - "functions"
  $i = 0;
  $functssect = "";
  $functsoff = "";

  while($functsoff !~ /.+/) {
    # sysseek to the i-th symbol
    sysseek($handle, $symtaboff + $i * 16, &SEEK_SET);

    (sysread($handle, $temp, 4) == 4) || die "$prog: error reading $fname: $!";
    $temp = unpack("I", $temp);

    if ($temp != 0) {
      # look up the name in the string table and see if it's "functions"
      sysseek($handle, $strtaboff + $temp, &SEEK_SET);

      (sysread($handle, $temp, 9) == 9) || die "$prog: error reading $fname - cannot find functions\nYou need to access the functions global variable for the linker to include it\n\t$!";

      # If we finally found the "functions"
      if ($temp =~ /functions/) {
	# sysseek to the section offset
	sysseek($handle, $symtaboff + $i * 16 + 4, &SEEK_SET);

	(sysread($handle, $functsoff, 4) == 4) || die "$prog: error reading $fname: $!";
	$functsoff = unpack("I", $functsoff);

	# sysseek to the section offset
	sysseek($handle, $symtaboff + $i * 16 + 14, &SEEK_SET);

	(sysread($handle, $functssect, 2) == 2) || die "$prog: error reading $fname: $!";
	$functssect = unpack("S", $functssect);
      }
    }
    $i++;
  }

  sysseek($handle, $shoff + $functssect * $shentsize, &SEEK_SET);
  sysread($handle, $temp, 4);
  $temp = unpack("I", $temp);

  sysseek($handle, $shstrtaboff + $temp,  &SEEK_SET);
  sysread($handle, $temp, 7);

  print "functions pointer in section $temp\n" if $verbose;

  # sysseek to the address in the section header for the section containing "functions"
  sysseek($handle, $shoff + $functssect * $shentsize + 12, &SEEK_SET);

  (sysread($handle, $temp, 4) == 4) || die "$prog: error reading $fname: $!";
  $temp = unpack("I", $temp);

  $functsoff = $functsoff - $temp;

  # sysseek to the offset in the section header for the section containing  "functions"
  sysseek($handle, $shoff + $functssect * $shentsize + 16, &SEEK_SET);

  (sysread($handle, $functssectoff, 4) == 4) || die "$prog: error reading $fname: $!";
  $functssectoff = unpack("I", $functssectoff);

  # now that we know where to sysseek to find functions we can go there

  sysseek($handle, $functssectoff + $functsoff, &SEEK_SET);

  $handle;
}
