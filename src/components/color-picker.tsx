import React, { useEffect } from 'react';
import { ChromePicker, SwatchesPicker } from 'react-color';
import IconButton from './icon-button';
import { BiPalette, BiGrid } from 'react-icons/bi';
import { useWasmContext } from '@/context/wasm';
import {
  Popover,
  PopoverTrigger,
  PopoverContent,
  Button,
  Flex,
  Box,
} from '@chakra-ui/react';

export const ColorIndicator = () => {
  const { fill, stroke } = useWasmContext();

  return (
    <Box
      rounded={'full'}
      w={'40px'}
      h={'40px'}
      bg={fill}
      border={`3px solid ${stroke}`}
    />
  );
};

export const SwatchesPickerButton = () => {
  const { module, setFill, fill } = useWasmContext();

  const handleChange = (e: React.MouseEvent) => {
    // e.preventDefault();
    console.log(e);
    console.log('right click');
  };

  return (
    <Popover placement="top-start">
      <PopoverTrigger>
        <Button onClick={handleChange} size={'sm'}>
          Color
        </Button>
      </PopoverTrigger>
      <PopoverContent width={500} p={2}>
        <Flex gap={2}>
          <ChromePicker
            color={fill}
            onChangeComplete={(c) => {
              module.setFill(c.hex);
              setFill(c.hex);
            }}
          />
          <SwatchesPicker
            color={fill}
            onChangeComplete={(c) => {
              module.setFill(c.hex);
              setFill(c.hex);
            }}
          />
        </Flex>
      </PopoverContent>
    </Popover>
  );
};
