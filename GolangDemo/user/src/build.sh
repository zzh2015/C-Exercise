#!/bin/bash
export GOPATH=$HOME/SampleWorkSpace/GoProject/user
export GOBIN=$HOME/SampleWorkSpace/GoProject/user/bin
echo $GOPATH
echo $GOBIN
go build hello/print
go install hello/print

go build hello
go install hello

$GOBIN/hello
