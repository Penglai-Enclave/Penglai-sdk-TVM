all:
	# Serverless Image functions
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C serverless-user 
	make -C imageErosion
	make -C imageRotate
	make -C imageResize
	make -C entry_enclave
	# Onefunc Baseline Image functions
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C baseline-onefunc/onefunc-user 
	make -C baseline-onefunc/image_enclave
	# Linux Base Image Functions
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C baseline-linux/serverless-user
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C baseline-linux/entry_func
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C baseline-linux/imageResize
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C baseline-linux/imageRotate
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C baseline-linux/imageErosion
	# copy to a serverless_test dir
	rm serverless_test -rf && mkdir serverless_test
	cp imageErosion/imageErosion serverless_test/
	cp imageResize/imageResize serverless_test/
	cp imageRotate/imageRotate serverless_test/
	cp entry_enclave/entry_enclave serverless_test/
	cp serverless-user/serverless-user serverless_test
	mkdir -p serverless_test/baseline-onefunc
	cp baseline-onefunc/onefunc-user/onefunc-user serverless_test/baseline-onefunc
	cp baseline-onefunc/image_enclave/image_enclave serverless_test/baseline-onefunc
	mkdir -p serverless_test/baseline-linux
	cp baseline-linux/imageErosion/imageErosion serverless_test/baseline-linux
	cp baseline-linux/imageResize/imageResize serverless_test/baseline-linux
	cp baseline-linux/imageRotate/imageRotate serverless_test/baseline-linux
	cp baseline-linux/entry_func/entry serverless_test/baseline-linux
	cp baseline-linux/serverless-user/serverless-user serverless_test/baseline-linux
	# copy scripts
	cp scripts/run_enclave_serverless.sh serverless_test
	cp scripts/run_enclave_onefunc.sh serverless_test/baseline-onefunc
	cp scripts/run_baseline_linux.sh serverless_test/baseline-linux

clean:
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C serverless-user clean
	make -C imageErosion clean
	make -C imageRotate clean
	make -C imageResize clean
	make -C entry_enclave clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C baseline-onefunc/onefunc-user clean
	make -C baseline-onefunc/image_enclave clean
	# Linux Base Image Functions
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C baseline-linux/serverless-user clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C baseline-linux/entry_func clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C baseline-linux/imageResize clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C baseline-linux/imageRotate clean
	rm serverless_test -rf
	rm sod-lib/*.o -rf
