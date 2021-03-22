## Serverless Image Processing

This is a demo to utilize Penglai for serverless computing.

### Build

Following the README in the top directory to build the whole image, the serverless computing demo is built by default.

### How to run

after load the penglai.ko module and mknod.sh

	cd serverless_test/
	# The following script run all the tests used in the paper
	./run_enclave_serverless.sh

You can also run simple case:

	./serverless-user 32 entry_enclave imageResize imageRotate imageErosion


You can enter the serverless_test/baseline_onefunc and serverless_test/baseline_linux to run two baseline benchmarks.
