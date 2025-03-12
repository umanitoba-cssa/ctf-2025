with open('warped_qr.pdf', 'rb') as w, open('unwarped_qr.pdf', 'wb') as u:
    while(byte := w.read(1)):
        if byte == b'\r':
            continue
        u.write(byte)