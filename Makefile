default:
	cmake -Bbuild .
	cmake --build build -j$(nproc --all)

clean:
	rm -rf build
