#!/bin/bash
export GOPATH=$HOME/SampleCodes/CPP-Exercise/GolangDemo/user
export GOBIN=$HOME/SampleCodes/CPP-Exercise/GolangDemo/user/bin
echo $GOPATH
echo $GOBIN
go build hello/print
go install hello/print

go build hello
go install hello

$GOBIN/hello
