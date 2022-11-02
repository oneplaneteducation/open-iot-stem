function Decoder(bytes, port) {

    let result = "";
    
    for (var i = 0; i < bytes.length; i++) {
      if (bytes[i] < 10) {
        result += 0;
        result += bytes[i];
      }else{
        result += bytes[i];
      }
    }
    
    let temp = result.slice(0, 4);
    let press = result.slice(4, 8);
    let humidity = result.slice(8, 10);
    let iaq_accuracy = result.slice(10, 11); 
    
    let static_iaq; 
    if (result.slice(11, 12) == "0" ) 
    {
       static_iaq = result.slice(12, 14);
    }
    else
    {
       static_iaq = result.slice(11, 14);
    }
    
    let co2 = result.slice(14);
  
    
    return {
      field1: temp/100, 
      field2: press,
      field3: humidity,
      field4: iaq_accuracy,
      field5: static_iaq,
      field6: co2*10
    };
  }
