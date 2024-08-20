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
  const { module } = useWasmContext();

  let fill = 'transparent';
  let stroke = 'black';

  useEffect(() => {
    fill = module?.getSelectFillColor();
    stroke = module?.getSelectStrokeColor();
  }, [module]);

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
  const { module } = useWasmContext();
  const [color, setColor] = React.useState('#fff');

  return (
    <Popover placement="top-start">
      <PopoverTrigger>
        <Button size={'sm'}>Color</Button>
      </PopoverTrigger>
      <PopoverContent width={500} p={2}>
        <Flex gap={2}>
          <ChromePicker
            color={color}
            onChangeComplete={(c) => {
              module.setSelectFillColor(c.hex);
              setColor(c.hex);
            }}
          />
          <SwatchesPicker
            color={color}
            onChangeComplete={(c) => {
              module.setSelectFillColor(c.hex);
              setColor(c.hex);
            }}
          />
        </Flex>
      </PopoverContent>
    </Popover>
  );
};
