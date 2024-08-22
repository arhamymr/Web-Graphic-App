'use client';

import { Box, Center } from '@chakra-ui/react';
import React, {
  createContext,
  useContext,
  useState,
  useEffect,
  Dispatch,
} from 'react';

type setColor = Dispatch<React.SetStateAction<string>>;
interface WasmContextProps {
  module: any;
  fill: string;
  stroke: string;
  setStroke: setColor;
  setFill: setColor;
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
  const [fill, setFill] = useState<string>('#fff');
  const [stroke, setStroke] = useState<string>('#000');

  const loadWasm = async () => {
    try {
      const loadmodule = await import('@/wasm/main.js');
      const instance = await loadmodule.default();
      instance.canvas = document.getElementById('canvas');
      const myModule = new instance.App(screen.w, screen.h);

      setModule(myModule);
      myModule.mainLoop();
      myModule.drawBackgroundGrid();
      instance.delete();
    } catch (error) {
      console.error(error);
    } finally {
      setLoading(false);
    }
  };

  console.log(module, 'module');

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
        <Center>
          <div>Loading...</div>
        </Center>
      ) : (
        <Box overflow={'hidden'} bg={'gray.500'} w={'full'} h={'full'}>
          <WasmContext.Provider
            value={{
              module,
              fill,
              stroke,
              setFill,
              setStroke,
            }}
          >
            <canvas
              id="canvas"
              className="w-full"
              width={screen.w}
              height={screen.h}
            ></canvas>
            {children}
          </WasmContext.Provider>
        </Box>
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
