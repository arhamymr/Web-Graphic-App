import React from 'react';
import IconButton from './icon-button';
import { BiSquare, BiPencil, BiImageAdd } from 'react-icons/bi';
import ColorPicker from './color-picker';
import { useWasmContext } from '@/context/wasm';
interface ToolbarProps {
  icon: React.ReactNode | string;
  onClick: () => void;
  disabled?: boolean;
}

const Toolbar: React.FC = () => {
  const { module } = useWasmContext();
  console.log(module, 'module context');

  const buttons: ToolbarProps[] = [
    {
      icon: <BiPencil size={'24px'} className="hover:text-primary" />,
      onClick: () => {
        module.pause();
      },
    },
    {
      icon: <BiSquare size={'24px'} className="hover:text-primary" />,
      onClick: () => {
        module.resume();
      },
    },
    {
      icon: <BiImageAdd size={'24px'} className="hover:text-primary" />,
      onClick: () => {
        alert('World');
      },
    },
  ];

  return (
    <div className="bg-white px-4 py-2 rounded absolute bottom-10 left-1/2 transform -translate-x-1/2 flex gap-6 border">
      {buttons.map((button, index) => (
        <IconButton key={index} icon={button.icon} onClick={button.onClick} />
      ))}

      <ColorPicker />
    </div>
  );
};

export default Toolbar;
