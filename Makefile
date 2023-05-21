default:
	cmake -Bbuild .
	cmake --build build -j$(nproc --all)
