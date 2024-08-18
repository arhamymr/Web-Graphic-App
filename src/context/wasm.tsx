'use client';

import React, { createContext, useContext, useState, useEffect } from 'react';

interface WasmContextProps {
  module: any;
}

const WasmContext = createContext<WasmContextProps | undefined>(undefined);

export const WasmProvider: React.FC<{ children: React.ReactNode }> = ({
  children,
}) => {
  const [isLoading, setLoading] = useState<boolean>(true);
  const [module, setModule] = useState<any>(null);
  const [screen, setScreen] = useState<{ w: number; h: number }>({
    w: 0,
    h: 0,
  });

  const loadWasm = async () => {
    try {
      const loadmodule = await import('@/wasm/main.js');
      const instance = await loadmodule.default();
      instance.canvas = document.getElementById('canvas');
      const myModule = new instance.App(screen.w, screen.h);
      setModule(myModule);
      myModule.mainLoop();
    } catch (error) {
      console.error(error);
    } finally {
      setLoading(false);
    }
  };

  useEffect(() => {
    if (typeof window !== 'undefined') {
      setScreen({
        w: window.innerWidth,
        h: window.innerHeight,
      });

      loadWasm();
    }
  }, [screen.w, screen.h]);

  return (
    <>
      {isLoading ? (
        <div className="fixed top-0 left-0 w-full h-full bg-black bg-opacity-50 flex items-center justify-center">
          <div className="text-white">Loading...</div>
        </div>
      ) : (
        <div className="bg-black w-full h-full">
          <canvas
            id="canvas"
            className="w-full"
            width={screen.w}
            height={screen.h}
          ></canvas>
          <WasmContext.Provider value={{ module }}>
            {children}
          </WasmContext.Provider>
        </div>
      )}
    </>
  );
};

export const useWasmContext = (): any => {
  const context = useContext(WasmContext);
  console.log(context, 'context');
  if (context === undefined) {
    throw new Error('useWasmContext must be used within a MyProvider');
  }
  return context;
};
