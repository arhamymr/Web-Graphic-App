import { WasmProvider } from '@/context/wasm';

export const Provider: React.FC<{ children: React.ReactNode }> = ({
  children,
}) => {
  return <WasmProvider>{children}</WasmProvider>;
};
