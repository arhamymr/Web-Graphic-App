import React from 'react';
import { IconButton as IconBtn } from '@chakra-ui/react';
interface IconButtonProps {
  icon: React.ReactElement<any>;
  onClick?: (val: any) => void;
  disabled?: boolean;
}

const IconButton: React.FC<IconButtonProps> = ({
  icon,
  onClick,
  disabled = false,
}) => {
  return (
    <IconBtn
      variant="outline"
      aria-label={'button'}
      onClick={onClick}
      size="sm"
      disabled={disabled}
      icon={icon}
    />
  );
};

export default IconButton;
