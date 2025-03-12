with open('evidence_d2FycGVk.pdf', 'rb') as m, open('solution.pdf', 'wb') as d:
    while(byte := m.read(1)):
        if byte == b'\r':
            continue
        d.write(byte)