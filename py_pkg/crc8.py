import crcmod.predefined

def calculate_crc8(data, byteorder='big'):
    crc8_func = crcmod.predefined.Crc('crc-8-rohc')
    crc8_func.update(data)
    crc_value = crc8_func.crcValue
    return crc_value.to_bytes(1, byteorder=byteorder)