
ALL_HEADER = all.h config.h \
		     src\core\or_p.h \
			 src\core\and_p.h \
			 src\core\not_p.h \
			 src\core\optional_p.h \
			 src\core\parser_base.h \
			 src\core\rule.h \
			 src\core\scanner.h \
			 src\core\repeat_p.h \
			 src\core\literal_p.h \
			 src\core\list_p.h \
			 src\core\difference_p.h \
			 src\core\action_parser.h \
			 src\core\compposer.h \
			 src\extentions\character_parsers.h \
			 src\extentions\scanner_policy.h \
			 src\utility\meta_fuctions.h \
			 src\utility\tuple_serialization.h \
			 src\utility\optional.h \
			 src\utility\alternative.h \
			 src\action\converters.h \
			 src\action\accumulater.h \
			 src\action\back_inserter.h \
			 src\action\combiner.h \
			 src\action\printer.h \
			 src\action\condition.h \
			 src\action\comparer.h \

all_test: test_and_p test_or_p test_repeat test_list test_optional test_rule test_json

test_and_p: unit_test/test_and_p.cc ${ALL_HEADER}
	g++ unit_test/test_and_p.cc -o bin/test_and_p -std=c++0x
	echo "test_and_p done!"
test_or_p: unit_test/test_or_p.cc ${ALL_HEADER}
	g++ unit_test/test_or_p.cc -o bin/test_or_p -std=c++0x
	echo "test_or_p done!"
test_repeat: unit_test/test_repeat.cc ${ALL_HEADER}
	g++ unit_test/test_repeat.cc -o bin/test_repeat -std=c++0x
	echo "test_repeat done!"
test_list: unit_test/test_list.cc ${ALL_HEADER}
	g++ unit_test/test_list.cc -o bin/test_list -std=c++0x
	echo "test_list done!"
test_optional: unit_test/test_optional.cc ${ALL_HEADER}
	g++ unit_test/test_optional.cc -o bin/test_optional -std=c++0x
	echo "test_optional done!"
test_difference: unit_test/test_difference.cc
	g++ unit_test/test_difference.cc -o bin/test_difference -std=c++0x
	echo "test_difference done!"
test_not_p: unit_test/test_not_p.cc
	g++ unit_test/test_not_p.cc -o bin/test_not_p -std=c++0x
	echo "test_not_p done!"
test_json: unit_test/test_json.cc
	g++ unit_test/test_json.cc -o bin/test_json -std=c++0x
	echo "test_json done!"
test_rule: unit_test/test_rule.cc
	g++ unit_test/test_rule.cc -o bin/test_rule -std=c++0x
	echo "test_rule done!"
clean: 
	rm -f bin/*.o
