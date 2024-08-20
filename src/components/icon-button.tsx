import React from 'react';
import { Icon } from '@chakra-ui/react';
import { IconType } from 'react-icons';
interface IconButtonProps {
  icon: IconType;
  onClick?: (val: any) => void;
}

const IconButton: React.FC<IconButtonProps> = ({ icon, onClick }) => {
  return (
    <Icon
      cursor={'pointer'}
      w={6}
      h={6}
      as={icon}
      aria-label={'button'}
      onClick={onClick}
    />
  );
};

export default IconButton;
