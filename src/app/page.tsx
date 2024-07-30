'use client';

// import { useWasmContext } from '@/context/wasm';
import { useRef } from 'react';

export default function Home() {
  const canvasRef = useRef<HTMLCanvasElement>(null);

  // const { module } = useWasmContext();

  return (
    <main className="flex min-h-screen flex-col items-center p-24">
      <canvas ref={canvasRef} id="canvas" width="640" height="480"></canvas>
      <p> web assembly getting started </p>

      {/* <button
        onClick={() => {
          module.initSDL();
        }}
      >
        init
      </button>
      <button
        onClick={() => {
          module.sayHi();
        }}
      >
        button with sdl
      </button> */}
      {/* <button
        onClick={() => {
          if (module) {
            module._sayHi();
          }
        }}
      >
        click
      </button> */}
    </main>
  );
}
