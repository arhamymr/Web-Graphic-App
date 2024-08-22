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


SOURCE_FILES="cpp/app.cpp cpp/object.cpp cpp/binding.cpp cpp/colors.cpp"

# build command 
emcc ${SOURCE_FILES} -o ${OUTPUT_JS} \
  -s EXPORT_ES6=1 \
  -s 'EXPORT_NAME="myModule"' \
  -s 'ENVIRONMENT="web"' \
  -s USE_SDL=2 \
  -s ALLOW_MEMORY_GROWTH=1 \
  -s MIN_SAFARI_VERSION=-1 \
  -s USE_SDL_GFX=2 \
  -Wall -g\
  --bind 

if [ $? -ne 0 ]; then echo "Linking failed"; exit 1; fi

