'use client';
import { WasmProvider } from '@/context/wasm';

import { CacheProvider } from '@chakra-ui/next-js';
import { ChakraProvider } from '@chakra-ui/react';

export function Providers({ children }: { children: React.ReactNode }) {
  return (
    <CacheProvider>
      <ChakraProvider>
        <WasmProvider>{children}</WasmProvider>;
      </ChakraProvider>
    </CacheProvider>
  );
}
