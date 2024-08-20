import React from 'react';
import IconButton from './icon-button';
import { BiSquare, BiPencil, BiImageAdd, BiGrid } from 'react-icons/bi';
import { ColorIndicator, SwatchesPickerButton } from './color-picker';
import { useWasmContext } from '@/context/wasm';
import { Box, Card, Center, Flex } from '@chakra-ui/react';
interface ToolbarProps {
  icon: React.ReactElement<any>;
  onClick: () => void;
  disabled?: boolean;
}

const Toolbar: React.FC = () => {
  const { module } = useWasmContext();

  const buttons: ToolbarProps[] = [
    {
      icon: <BiPencil />,
      onClick: () => {
        module.pause();
      },
    },
    {
      icon: <BiSquare />,
      onClick: () => {
        module.resume();
      },
    },
    {
      icon: <BiImageAdd />,
      onClick: () => {
        alert('World');
      },
    },
  ];

  return (
    <Box
      position="absolute"
      bottom="20px"
      left="50%"
      transform="translate(-50%, -50%)"
    >
      <Flex gap={2} align={'center'}>
        <Card>
          <Flex gap={1} px={4} py={2} border={'1px solid gray.200'}>
            {buttons.map((button, index) => (
              <IconButton
                key={index}
                icon={button.icon}
                onClick={button.onClick}
              />
            ))}

            <SwatchesPickerButton />
          </Flex>
        </Card>
        <ColorIndicator />
      </Flex>
    </Box>
  );
};

export default Toolbar;
