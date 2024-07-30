MODULE_NAME=cpp/main.cpp
OUTPUT_JS=cpp/main.js

mkdir -p src/wasm

# build command 
emcc ${MODULE_NAME} -o ${OUTPUT_JS} \
  -s 'ENVIRONMENT="web"' \
  -s USE_SDL=2 \
  -s MIN_SAFARI_VERSION=-1 \
  --bind

