
ALL_HEADER = all.h config.h \
		     src/compound/alternative_p.h \
			 src/compound/diference_p.h \
			 src/compound/list_p.h \
			 src/compound/literal_p.h \
			 src/compound/not_p.h \
			 src/compound/optional_p.h \
			 src/compound/repeat_p.h \
			 src/compound/sequence_p.h \
			 src/parsers/parsers.h \
			 src/utility/alternative.h \
			 src/utility/data_holder.h \
			 src/utility/meta_fuctions.h \
			 src/utility/optional.h \
			 src/utility/tuple_serialization.h

all_test: test_squence test_alternative_p test_repeat test_list test_optional test_alternative

test_squence: unit_test/test_squence.cc ${ALL_HEADER}
	g++ unit_test/test_squence.cc -o bin/test_squence -std=c++0x
	echo "test_squence done!"
test_alternative_p: unit_test/test_alternative_p.cc ${ALL_HEADER}
	g++ unit_test/test_alternative_p.cc -o bin/test_alternative_p -std=c++0x
	echo "test_alternative_p done!"
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


clean: 
	rm -f bin/*.o
