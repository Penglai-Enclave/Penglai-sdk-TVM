all:
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C sync_ipc_client
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C sync_ipc_server
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C sync_ipc_host
	rm -rf sync_ipc
	mkdir sync_ipc
	cp sync_ipc_client/sync_ipc_client sync_ipc
	cp sync_ipc_server/sync_ipc_server sync_ipc
	cp sync_ipc_host/host sync_ipc

clean:
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C sync_ipc_client clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C sync_ipc_server clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C sync_ipc_host clean