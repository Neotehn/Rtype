BIN = bin
BUILD = build

install:
	pip install conan
	make build

build: normdir conan
	cmake -S . -B $(BUILD);
	cmake --build $(BUILD);
	#cp r-type_client ./r-type_server

test: testdir conan
	cmake -S . -B $(BUILD) -DTESTMODE=1;
	cmake --build $(BUILD);

coverage: cleantest test
	./bin/Tests
	./outputCoverage.sh

testdir:
	$(eval BUILD="test/build")

normdir:
	$(eval BUILD="build")

conan:
	conan install conanfile.txt -if $(BUILD) --build=missing -c tools.system.package_manager:mode=install
	cd $(BUILD)/ && chmod +x ./activate.sh && source ./activate.sh

cleanbuild: normdir clean

cleantest: testdir clean cleancoverage

cleancoverage:
	find . -name "*.gcno" -delete
	find . -name "*.gcda" -delete
	find . -name "*.gcov" -delete
	find . -name "*.html" -delete


clean:
	rm -rf $(BUILD);
	mkdir $(BUILD);
	rm -rf $(BIN)/*

rebuild: cleanbuild build

retest: testdir cleantest test