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
  const SCREEN_WIDTH = window.innerWidth;
  const SCREEN_HEIGHT = window.innerHeight;

  const [module, setModule] = useState<any>(null);

  const loadWasm = async () => {
    try {
      const loadmodule = await import('@/wasm/main.js');
      const instance = await loadmodule.default();
      instance.canvas = document.getElementById('canvas');
      const myModule = new instance.App(SCREEN_HEIGHT, SCREEN_WIDTH);
      myModule.mainLoop();
      setModule(myModule);
    } catch (error) {
      console.error(error);
    }
  };

  useEffect(() => {
    loadWasm();
  }, []);

  return (
    <div className="bg-black w-full h-full">
      <canvas
        id="canvas"
        className="w-full"
        width={SCREEN_WIDTH}
        height={SCREEN_HEIGHT}
      ></canvas>
      <WasmContext.Provider value={{ module, loadWasm }}>
        {children}
      </WasmContext.Provider>
    </div>
  );
};

export const useWasmContext = () => {
  const context = useContext(WasmContext);
  if (context === undefined) {
    throw new Error('useWasmContext must be used within a MyProvider');
  }
  return context;
};
