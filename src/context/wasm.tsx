'use client';

import React, {
  createContext,
  useContext,
  useState,
  useEffect,
  useRef,
} from 'react';
import Script from 'next/script';

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
    try {
      const loadmodule = await import('@/wasm/main.js');
      console.log(loadmodule, 'loadmodule');
      const instance = await loadmodule.default();
      console.log(instance);
      instance.canvas = document.getElementById('canvas');
      const myModule = new instance.App();

      myModule.draw();
      myModule.main_loop();
      setModule(myModule);
    } catch (error) {
      console.error(error);
    }
  };

  useEffect(() => {
    loadWasm();
  }, []);

  return (
    <>
      <WasmContext.Provider value={{ module, loadWasm }}>
        <canvas id="canvas" width="640" height="480"></canvas>
        {children}
      </WasmContext.Provider>
    </>
  );
};

export const useWasmContext = () => {
  const context = useContext(WasmContext);
  if (context === undefined) {
    throw new Error('useWasmContext must be used within a MyProvider');
  }
  return context;
};
