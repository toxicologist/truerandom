import serial

class ReadLine:
    def __init__(self, s):
        self.buf = bytearray()
        self.s = s

    def readline(self):
        i = self.buf.find(b"\n")
        if i >= 0:
            r = self.buf[:i+1]
            self.buf = self.buf[i+1:]
            return r
        while True:
            i = max(1, min(2048, self.s.in_waiting))
            data = self.s.read(i)
            i = data.find(b"\n")
            if i >= 0:
                r = self.buf + data[:i+1]
                self.buf[0:] = data[i+1:]
                return r
            else:
                self.buf.extend(data)
                
class Conn():
    def init(self, port):
        self.ser = serial.Serial(port, 9600, timeout=1, write_timeout=1)

        self.rl = ReadLine(self.ser)
        
        self.ser.write('init\n'.encode())
        print(self.rl.readline())
        
    def command(self, command):
        self.ser.write(f'{command}\n'.encode())
        
        #return ser.read(length)
        return self.rl.readline().decode('utf-8').split('\r\n')[0]

c = Conn()

def bit():
    return c.command('bit\n')

def byte():
    return c.command('byte\n')

def range(lower, upper):
    command = "range%s%s%s%s\n" % (len(str(lower)), len(str(upper)), lower, upper)
    return c.command(command)

def init(port):
    global c
    c.init(port)

    
