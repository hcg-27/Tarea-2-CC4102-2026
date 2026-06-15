CXX = $(shell command -v g++-14 2> /dev/null || command -v g++-13 2> /dev/null || echo g++)
CXXFLAGS = -std=c++23 -I./include -O2 -Wall -Wextra

BUILD_DIR = build
OUT_DIR = out
DATA_DIR = data

AVL_OBJ = $(BUILD_DIR)/avl.o

EXPERIMENTOS = $(OUT_DIR)/crear_datasets \
               $(OUT_DIR)/ia_bu $(OUT_DIR)/ia_bs \
               $(OUT_DIR)/io_bu $(OUT_DIR)/io_bs \
               $(OUT_DIR)/sat $(OUT_DIR)/wst

.PHONY: all check setup clean

all: setup check $(EXPERIMENTOS)

check:
	@command -v $(CXX) >/dev/null 2>&1 || { echo "Error: g++ no está instalado"; exit 1; }
	@$(CXX) -dumpversion | awk -F. '{ if ($$1 < 13) { print "Error: se requiere GCC >= 13"; exit 1 } }'
	@echo "Todas las dependencias están instaladas. Usando compilador: $(CXX)"

setup:
	@mkdir -p $(DATA_DIR) $(OUT_DIR) $(BUILD_DIR)

$(BUILD_DIR)/avl.o: src/arboles/avl.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUT_DIR)/crear_datasets: src/experimentos/base/crear_datasets.cpp
	$(CXX) $(CXXFLAGS) $< -o $@


$(OUT_DIR)/ia_bu: src/experimentos/base/ia_bu.cpp $(AVL_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OUT_DIR)/ia_bs: src/experimentos/base/ia_bs.cpp $(AVL_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OUT_DIR)/io_bu: src/experimentos/base/io_bu.cpp $(AVL_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OUT_DIR)/io_bs: src/experimentos/base/io_bs.cpp $(AVL_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OUT_DIR)/sat: src/experimentos/teoremas/sat.cpp $(AVL_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OUT_DIR)/wst: src/experimentos/teoremas/wst.cpp $(AVL_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD_DIR)/* $(OUT_DIR)/* $(DATA_DIR)/*.bin