import React from 'react';
import { ChromePicker } from 'react-color';
import IconButton from './icon-button';
import { BiPalette } from 'react-icons/bi';
const ColorPicker = () => {
  const [color, setColor] = React.useState('#fff');
  const [showPicker, setShowPicker] = React.useState(false);

  return (
    <div className="flex">
      <IconButton
        icon={<BiPalette size={'23px'} className="hover:text-primary" />}
        onClick={() => setShowPicker(!showPicker)}
      />
      {showPicker && (
        <div className="absolute bottom-12">
          <ChromePicker
            color={color}
            onChangeComplete={(c) => setColor(c.hex)}
          />
        </div>
      )}
    </div>
  );
};

export default ColorPicker;
