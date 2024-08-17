# Cleanup object files

TARGET_DIR=src/wasm
OUTPUT_JS=${TARGET_DIR}/main.js

mkdir -p src/wasm

if [ -f "${TARGET_DIR}/main.js" ]; then
    rm "${TARGET_DIR}/main.js"
fi

if [ -f "${TARGET_DIR}/main.wasm" ]; then
    rm "${TARGET_DIR}/main.wasm"
fi


# build command 
emcc cpp/app.cpp cpp/object_item.cpp cpp/binding.cpp -o ${OUTPUT_JS} \
  -s EXPORT_ES6=1 \
  -s 'EXPORT_NAME="myModule"' \
  -s 'ENVIRONMENT="web"' \
  -s USE_SDL=2 \
  -Wall -g\
  --bind 

if [ $? -ne 0 ]; then echo "Linking failed"; exit 1; fi

