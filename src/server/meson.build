install_headers(
	[
	'socket.hpp',
	],
	subdir: 'stardustxr/server'
)
server_files = files(
	'socket.cpp'
)
lib_server = library(
	'stardustxr-server',
	[common_files, server_files],
	dependencies: [threads],
	version: '0.9.0',
	soversion: '0',
	install: true
)
pkg.generate(lib_server, filebase: 'stardustxr-server', name: 'stardustxr-server', url: 'https://github.com/StardustXR/libstardustxr')
