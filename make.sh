MODULE_NAME=cpp/main.cpp
OUTPUT_JS=src/wasm/main.js
# EXPORTED_FUNCTIONS=_main,_sayHi
# EXPORTED_RUNTIME_METHODS=ccall,cwrap

# Create the directory if it doesn't exist
mkdir -p src/wasm

# build command 
emcc ${MODULE_NAME} -o ${OUTPUT_JS} \
  -s EXPORT_ES6=1 \
  -s 'EXPORT_NAME="myModule"' \
  -s 'ENVIRONMENT="web"' \
  -s USE_SDL=2 \
  --bind

