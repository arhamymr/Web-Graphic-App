'use client';

import { useWasmContext } from '@/context/wasm';

export default function Home() {
  const { module } = useWasmContext();

  return (
    <main className="flex min-h-screen flex-col items-center p-24">
      <p> web assembly getting started </p>
      <button
        onClick={() => {
          const myClass = new module.MyClass();
          myClass.sayHi();
        }}
      >
        button with class
      </button>
      <button
        onClick={() => {
          if (module) {
            module._sayHi();
          }
        }}
      >
        click
      </button>
    </main>
  );
}
