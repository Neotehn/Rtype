BUILD = build

install:
	pip install conan
	make build

build: normdir conan
	cmake -S . -B $(BUILD);
	cmake --build $(BUILD) --config Release;
	#cp r-type_client ./r-type_server

normdir:
	$(eval BUILD="build")

conan:
	conan install conanfile.txt -if $(BUILD) --build=missing
	cd $(BUILD)/ && chmod +x ./activate.sh && source ./activate.sh
	echo "Conan env running"

cleanbuild: normdir clean


cleancoverage:
	find . -name "*.gcno" -delete
	find . -name "*.gcda" -delete
	find . -name "*.gcov" -delete
	find . -name "*.html" -delete


clean:
	rm -rf $(BUILD);
	mkdir $(BUILD);

rebuild: cleanbuild build