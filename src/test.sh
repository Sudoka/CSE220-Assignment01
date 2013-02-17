#!/bin/bash
#***************************************************************************************************************
# SHELL SCRIPT: test.sh
#
# DESCRIPTION
# Tests the English Language Letter Frequency Analyzer program.
#
# AUTHOR INFORMATION
# Kevin R. Burger [KRB]
#
# Mailing Address:
# Computer Science & Engineering
# School of Computing, Informatics, and Decision Systems Engineering
# Arizona State University
# Tempe, AZ 85287-8809
#
# Email: burgerk@asu
# Web:   http://kevin.floorsoup.com
#***************************************************************************************************************

#----- TestEllfa -----------------------------------------------------------------------------------------------
# Analyze the text file $_text with the output in $_format format ($_format will be either csv or plain).
#---------------------------------------------------------------------------------------------------------------
TestEllfa() {
	# Set $ _base to the base name of the text file name, e.g., if $_text is "foo-bar.txt", this statement will
	# set $_base to "foo-bar". Note: this only works if the file name extension of the text file is ".txt".
	#
	# Bash shell scripts support a number of operations on strings. If v is a variable, then the replace opera-
	# tion is,
	#
	# ${v/search-for/replace-with}
	#
	# where 'search-for' is a string to be searched for in v and if search-for is found, that substring is re-
	# placed with 'replace_with'. In this case, we are searching for .txt and replacing it with nothing, ergo,
	# the file name extension (or suffix) is removed. The result is assigned to a new Bash variable $_base.
	#
	# Remember: when assigning to a Bash variable, we do not precede the variable name with $ but when the vari-
	# able is accessed, we do prefix it with $.
	_base=${_text/.txt/}

	# Set $_output to "my-" + $_base with $_format as the suffix, e.g., if $_text is "foo.txt" and $_format is
	# ".csv " then $_output will be "my-foo.csv"
	_output=my-${_base}.${_format}

	# Set $_correct to the name of the file containing the correct output.
	_correct=${_base}.${_format}

	# Set $_diff to the name of the output file from the diff command.
	_diff=${_base}.diff

	# Analyze the file and output in $_format format.
	echo -n "Testing ${_text}. Output will be in ${_format} format... "
	if [ $_format = "csv" ]; then
		_option="-c"
	else
		_option=
	fi
	${_binary} ${_option} -f ${_text} -o ${_output}

	# Compare the program's output to the correct output. If the files are identical, then diff will output
	# nothing, so $_diff will not be created.
	diff -w ${_output} ${_correct} > ${_diff}

	# See if the files match. The test -s command checks to see if the specified file exists. If it does not
	# then diff did not find any differences between the two files.
	if test -s ${_diff} ; then
		echo "FAIL"
	else # They match. Clean up.
		echo "pass"
		_passed=$((${_passed} + 1))
	fi
	rm -f ${_output}
	rm -f ${_diff}
}

#----- TestEllfaOpt --------------------------------------------------------------------------------------------
# 
#---------------------------------------------------------------------------------------------------------------
TestEllfaOpt() {
	echo -n $_msg
	${_binary} ${_options} > __test__
	grep -F -q "${_grep_str}" __test__
	if [ "$?"=0 ] ; then
		echo "pass"
		_passed=$((${_passed} + 1))
	else
		echo "FAIL"
	fi
	rm -f __test__
}

#---------------------------------------------------------------------------------------------------------------
# Starting point of execution for the shell script.
#---------------------------------------------------------------------------------------------------------------

# The number of test cases to perform.
_num_test_cases = 40

# _binary is the name of the executable program (i.e., in Unix lingo this is called a binary).
_binary=./ellfa

# $_passed is the number of test cases that passed. Initialize to 0.
_passed=0

# Store the current working directory in _cwd. We are going to cd to the testing directory and when we are done
# testing, we will cd back to the current directory.
_cwd=`pwd`

# This is the directory containing the test cases.
_testdir=test

# Copy the binary to the testing directory.
cp ${_binary} ${_testdir}

# cd to the testing directory.
cd ${_testdir}

# Let _text take on the values of each of the .txt file names. For each .txt file, call the TestEllfa()
# function twice, one time outputting the results in csv format and the next time in plain format.
for _text in $(ls *.txt) ; do
	_format="csv"
	TestEllfa
	_format="plain"
	TestEllfa
done

# Test that the correct error message is displayed if the file specified with the -f option cannot be opened.
_msg="Testing that the file specified with -f cannot be opened... "
_options=" -f __xyz__ "
_grep_str="could not open __xyz__"
TestEllfaOpt

# Test that the correct error message is displayed if the file specified with the -o option cannot be opened.
_msg="Testing that the file specified with -o cannot be opened... "
_options=" -o /bin/date " 
_grep_str="could not open /bin/date"
TestEllfaOpt

# Test that the -v option is handled correctly when it is the only option on the command line.
_msg="Testing for -v on command line... "
_options=" -v "
_grep_str="ellfa: version"

# Test that the -h option is handled correctly when it is the only option on the command line.
_msg="Testing for -h on command line... "
_options=" -h "
_grep_str="Usage: ellfa"
TestEllfaOpt

# Test that the -h and -v options are handled correctly when both are specified (-h has higher precedence).
_msg="Testing for -h and -v on command line... "
_options=" -h -v "
_grep_str="Usage: ellfa"
TestEllfaOpt
_msg="Testing for -v and -h on command line... "
_options=" -v -h "
_grep_str="Usage: ellfa"
TestEllfaOpt

# Test that the -f option with missing file name is handled correctly.
_msg="Testing for -f and missing file name on command line... "
_options=" -f "
_grep_str="expecting argument following -f"
TestEllfaOpt

# Test that the -o option with missing file name is handled correctly.
_msg="Testing for -o and missing file name on command line... "
_options=" -o "
_grep_str="expecting argument following -o"
TestEllfaOpt

# Test that an invalid option on the command line is handled correctly.
_msg="Testing for invalid option -x on command line... "
_options=" -x "
_grep_str="ellfa: invalid option -x"
TestEllfaOpt

# Test that an unexpected string on the command line is handled correctly.
_msg="Testing for unexpected string on command line... "
_options=" -v-f "
_grep_str="ellfa: unexpected string -v-f"
TestEllfaOpt

# Test that -h has highest precedence.
_msg="Testing that -h has highest precedence..."
_options=" -c -f foo -o bar -h -v"
_grep_str="Usage: ellfa"
TestEllfaOpt


rm -f __test__

# cd back to the original working directory.
cd ${_cwd}

# Display number of test cases that passed.
if [ ${_passed}=${_num_test_cases} ] ; then
	echo All test cases passed
else
	echo ${_passed} test cases passed
	echo $((${_num_test_cases} - ${_passed})) test cases failed
fi