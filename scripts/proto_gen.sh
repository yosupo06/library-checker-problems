TMPDIR=$(mktemp -d)

mkdir -p $TMPDIR/scripts
cp ../../library-checker-judge/api/proto/library_checker.proto $TMPDIR/scripts

python3 -m grpc_tools.protoc $TMPDIR/scripts/library_checker.proto \
    -I $TMPDIR \
    --python_out=.. \
    --grpc_python_out=..

rm -rf $TMPDIR