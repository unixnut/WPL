<?php
# TO-DO: 

namespace WPL;

// Base enumeration class
// See https://www.geeksforgeeks.org/enumerations-in-php/
abstract class BasicEnum {
  
    // Enumeration constructor
    final public function __construct($value) {
        try {
            $c = new \ReflectionClass($this);
  
            // Content validation
            if (!in_array($value, $c->getConstants())) {
                throw new \DomainException("Value not present in enum");
            }
            $this->value = $value;
        }
        catch (\Exception $k){
            error_log($k->getMessage());
        }
    }
  
    // String representation
    final public function __toString() {
        return $this->value;
    }
}


# vim: set tabstop=4 shiftwidth=4 :
# Local Variables:
# tab-width: 4
# end:
