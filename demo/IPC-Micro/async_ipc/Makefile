all:
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C async_ipc_client
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C async_ipc_server
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C async_ipc_host
	rm -rf async_ipc
	mkdir async_ipc
	cp async_ipc_client/async_ipc_client async_ipc
	cp async_ipc_server/async_ipc_server async_ipc
	cp async_ipc_host/host async_ipc

clean:
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C async_ipc_client clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C async_ipc_server clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C async_ipc_host clean