
ALL_HEADER = all.h config.h \
		     src/compound/or_p.h \
			 src/compound/diference_p.h \
			 src/compound/list_p.h \
			 src/compound/literal_p.h \
			 src/compound/not_p.h \
			 src/compound/optional_p.h \
			 src/compound/repeat_p.h \
			 src/compound/and_p.h \
			 src/parsers/basic_parsers.h \
			 src/parsers/rule.h \
			 src/parsers/type_tags.h \
			 src/parsers/compposer.h \
			 src/parsers/context_parser.h \
			 src/parsers/action_parser.h \
			 src/utility/meta_fuctions.h \
			 src/utility/tuple_serialization.h \
			 src/converter/converters.h \
			 src/converter/convert_traits.h \
			 src/action/accumulater.h \
			 src/action/back_inserter.h \
			 src/action/printer.h \
			 src/action/condition.h \
			 src/action/comparer.h

all_test: test_and_p test_or_p test_repeat test_list test_optional test_alternative

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
test_alternative: unit_test/test_alternative.cc
	g++ unit_test/test_alternative.cc -o bin/test_alternative -std=c++0x
	echo "test_alternative done!"
test_difference: unit_test/test_difference.cc
	g++ unit_test/test_difference.cc -o bin/test_difference -std=c++0x
	echo "test_difference done!"
test_not_p: unit_test/test_not_p.cc
	g++ unit_test/test_not_p.cc -o bin/test_not_p -std=c++0x
	echo "test_not_p done!"
clean: 
	rm -f bin/*.o
