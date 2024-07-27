MODULE_NAME=cpp/main.cpp
OUTPUT_JS=src/wasm/main.js
EXPORTED_FUNCTIONS=_main,_sayHi
EXPORTED_RUNTIME_METHODS=ccall,cwrap

# Create the directory if it doesn't exist
mkdir -p src/wasm

# build command 
emcc ${MODULE_NAME} -o ${OUTPUT_JS} \
  -s EXPORTED_FUNCTIONS=${EXPORTED_FUNCTIONS} \
  -s EXPORTED_RUNTIME_METHODS=${EXPORTED_RUNTIME_METHODS} \
  -s EXPORT_ES6=1 \
  -s 'EXPORT_NAME="myModule"' \
  -s 'ENVIRONMENT="web"'

