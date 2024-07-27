'use client';

import React, { createContext, useContext, useState, useEffect } from 'react';

interface WasmContextProps {
  module: any;
  loadWasm: () => void;
}

const WasmContext = createContext<WasmContextProps | undefined>(undefined);

export const WasmProvider: React.FC<{ children: React.ReactNode }> = ({
  children,
}) => {
  const [module, setModule] = useState<any>(null);

  const loadWasm = async () => {
    const loadmodule = await import('@/wasm/main.js');
    const myModule = await loadmodule.default();
    setModule(myModule);
  };

  useEffect(() => {
    loadWasm();
  }, []);

  return (
    <WasmContext.Provider value={{ module, loadWasm }}>
      {children}
    </WasmContext.Provider>
  );
};

export const useWasmContext = () => {
  const context = useContext(WasmContext);
  if (context === undefined) {
    throw new Error('useWasmContext must be used within a MyProvider');
  }
  return context;
};
