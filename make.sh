
TARGET_DIR=src/wasm
OUTPUT_JS=${TARGET_DIR}/main.js


mkdir -p src/wasm


# build command 
emcc cpp/app.cpp cpp/object.cpp cpp/binding.cpp -o ${OUTPUT_JS} \
  -s EXPORT_ES6=1 \
  -s 'EXPORT_NAME="myModule"' \
  -s 'ENVIRONMENT="web"' \
  -s USE_SDL=2 \
  --bind

if [ $? -ne 0 ]; then echo "Linking failed"; exit 1; fi

# Cleanup object files
# rm ${TARGET_DIR}/_main.o ${TARGET_DIR}/_object.o

