JAVAC = javac
JAR = jar
SRC_DIR = .
OUT_DIR = out
MAIN_CLASS = control.Main

DATA_DIR = data/ch9-1.1/inputs
GR_FILES := $(wildcard $(DATA_DIR)/**/*.gr)

.PHONY: all clean run run_dijkstra_time run_diala_time run_radix_time run_dijkstra_path run_diala_path run_radix_path run_tests gen_charts help


all: $(OUT_DIR)/dijkstra.jar

$(OUT_DIR)/dijkstra.jar: $(wildcard $(SRC_DIR)/*/*.java)
	@mkdir -p $(OUT_DIR)
	$(JAVAC) -d $(OUT_DIR) $^
	@echo "Main-Class: $(MAIN_CLASS)" > $(OUT_DIR)/manifest.txt
	$(JAR) cfm $@ $(OUT_DIR)/manifest.txt -C $(OUT_DIR) .
	@rm $(OUT_DIR)/manifest.txt

clean:
	rm -rf $(OUT_DIR)

run_dijkstra_time: $(OUT_DIR)/dijkstra.jar
	java -jar $< -a dijkstra -d $$D -ss $$SS -oss $$OSS

run_diala_time: $(OUT_DIR)/dijkstra.jar
	java -jar $< -a diala -d $$D -ss $$SS -oss $$OSS

run_radix_time: $(OUT_DIR)/dijkstra.jar
	java -jar $< -a radix -d $$D -ss $$SS -oss $$OSS

run_dijkstra_path: $(OUT_DIR)/dijkstra.jar
	java -jar $< -a dijkstra -d $$D -p2p $$P2P -op2p $$OP2P

run_diala_path: $(OUT_DIR)/dijkstra.jar
	java -jar $< -a diala -d $$D -p2p $$P2P -op2p $$OP2P

run_radix_path: $(OUT_DIR)/dijkstra.jar
	java -jar $< -a radix -d $$D -p2p $$P2P -op2p $$OP2P

run_tests: $(OUT_DIR)/dijkstra.jar
	@for file in $(GR_FILES); do \
		dir=$$(dirname $$file); \
		base=$$(basename $$file .gr); \
		for algorithm in dijkstra diala radix; do \
        			java -jar $< -a $$algorithm -d "$$file" -ss "$$dir/$$base.ss" -oss "$$dir/$$algorithm-$$base.ss.res"; \
        			java -jar $< -a $$algorithm -d "$$file" -p2p "$$dir/$$base.p2p" -op2p "$$dir/$$algorithm-$$base.p2p.res"; \
        		done \
	done

gen_charts:
	python3 scripts/chart_gen.py $$P

.PHONY: help
help:
	@echo "Available targets:"
	@echo "  all           : Compile and create the JAR file"
	@echo "  clean         : Remove compiled classes and JAR file"
	@echo "  run           : Run the program from the JAR file"
	@echo "  run_dijkstra_time  : Run the dijkstra algorithm with specified input files (-d -ss -oss)"
	@echo "  run_diala_time     : Run the diala algorithm with specified input files (-d -ss -oss)"
	@echo "  run_radix_time     : Run the radix algorithm with specified input files (-d -ss -oss)"
	@echo "  run_dijkstra_path  : Run the dijkstra algorithm with specified input files (-d -p2p -op2p)"
	@echo "  run_diala_path     : Run the diala algorithm with specified input files (-d -p2p -op2p)"
	@echo "  run_radix_path     : Run the radix algorithm with specified input files (-d -p2p -op2p)"
	@echo "  run_ss_res         : Generate .ss.res files in each folder"
	@echo "  run_p2p_res        : Generate .p2p.res files in each folder"
	@echo "  gen_charts     : Generate charts based on .ss files"
	@echo "  help          : Display this help message"
