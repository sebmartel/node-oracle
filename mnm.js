#!/usr/bin/env node

var path = require('path');
var Builder = require('mnm');
var builder = new Builder();

builder.appendUnique('CXXFLAGS', '-Isrc/');

var ociIncludeDir = process.env["OCI_INCLUDE_DIR"] || "/usr/include/oracle/11.2/client/";
builder.failIfNotExists(ociIncludeDir, 'Could not find "%s" check OCI_INCLUDE_DIR environment variable.');
builder.failIfNotExists(path.join(ociIncludeDir, 'occi.h'), 'Could not find "%s" check OCI_INCLUDE_DIR environment variable.');
builder.appendUnique('CXXFLAGS', [ '-I' + ociIncludeDir ]);

ociLibDir = process.env["OCI_LIB_DIR"] || "/usr/lib/oracle/11.2/client/lib/";
builder.failIfNotExists(ociLibDir, 'Could not find "%s" check OCI_LIB_DIR environment variable.');
builder.appendUnique('LINKFLAGS', [ '-L' + ociLibDir ]);

builder.appendLinkerLibrary("occi");
builder.appendLinkerLibrary("clntsh");
builder.appendLinkerLibrary("nnz11");

builder.target = "oracle_bindings"
builder.appendSourceDir('./src');

builder.run();
