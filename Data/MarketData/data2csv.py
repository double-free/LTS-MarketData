import sys
import struct

# https://docs.python.org/3/library/struct.html


header_fmt = 'QQII'

# XTP
xtp_body_formats = (
'i16sddddddddddddddqqdd10d10d10q10q\
q8sqqddddddiidddddddiiddddqqiiiii4sddd', # market data

'', # market index

'', # market order

''  # market trade
)

# LTS, no padding
# DO NOT CHANGE THE ORDER
lts_body_formats = (
'', # Unknown

'9s9s9s31sddddddccdddddddddddddii\
ddiddiddiddiddiddiddiddiddiddi\
ddiddiddiddiddiddiddiddiddiddi\
i4s7sddddddddddddddddddddddddddd', # market data

'9s9s9s31sdddddddd4s', # market index

'ii9s9s31sdd2s2s4s', # market order

'iiii9s9s31sdd2s2s2s4s'  # market trade
)

# parse bytes to tupple
def parseMsg(buf, msg_id):
    return struct.unpack(xtp_body_formats[msg_id], buf)

def generate_csv_from_data(dataFilePath):
    filePath = sys.argv[1]
    fileName = filePath.split('/')[-1]
    with open(filePath, 'rb') as dataf:
        # 如果已经存在 csv 则删除
        csvPath = filePath + '.csv'
        # if os.access(csvPath, os.R_OK):
        #     os.remove(csvPath)
        with open(csvPath, 'w') as csvf:
            readIdx = 0
            HEADER_SIZE = 24
            while True:
                # 读取 header
                dataf.seek(readIdx)
                buf = dataf.read(HEADER_SIZE)
                if len(buf) == 0:
                    return
                header = struct.unpack(header_fmt, buf)
                csvf.write(','.join('{0}'.format(x) for x in header) + '\n')
                readIdx += HEADER_SIZE
                # 读取 body
                msg_id = header[2]
                body_size = header[3]
                dataf.seek(readIdx)
                msg = parseMsg(dataf.read(body_size), msg_id)
                csvf.write(', '.join('{0}'.format(x) for x in msg) + '\n')
                readIdx += body_size


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("usage: python3 " + sys.argv[0] + " <Market data file>")
        exit(0)

    generate_csv_from_data(sys.argv[1])
