CXX = $(shell command -v g++-14 2> /dev/null || command -v g++-13 2> /dev/null || echo g++)
CXXFLAGS = -std=c++23 -I./include

BUILD_DIR = build
OUT_DIR = out
DATA_DIR = data

check:
	@command -v $(CXX) >/dev/null 2>&1 || { echo "Error: g++ no está instalado"; exit 1; }
	@$(CXX) -dumpversion | awk -F. '{ if ($$1 < 13) { print "Error: se requiere GCC >= 13"; exit 1 } }'
	@echo "Todas las dependencias están instaladas. Usando compilador: $(CXX)"

setup:
	mkdir -p $(DATA_DIR) $(OUT_DIR) $(BUILD_DIR)
