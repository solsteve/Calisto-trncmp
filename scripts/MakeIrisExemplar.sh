#!/bin/bash
cat<<EOF | base64 -d | zcat > iris_test.exm
H4sICD9gdF0CA2lyaXNfdGVzdC5leG0AdVJBEsQgCLv3FbzAEQHd/v9jG6jObNE9ONaGQAhIJSW5
rNwkBd+lERcjqoVxbr+vHiCTFaWGe4IRACYDFLAG3sG8VwCYFaAirSGgv9MafjYcRRAjQ6rZAN4A
ZQctWK5U8W65poD5IRf208pS22effKo5QpCBzTgv5og+K7lTmwmuUqKN599LkNd0QRrMmgW5CfLP
hAqwTbBmE1yQnU2waKXPgMRUiPGpcLw3Jk/Q/qV1h+qpFZ3McWIu4+20YBLD9qDN+Ae0sG9j+qga
6kmALaflWbOHS4nZ5hbYPrIeKRkB46R2xMYvM5JazXv7zA739QWxAizYbQMAAA==
EOF

cat<<EOF | base64 -d | zcat > iris_train.exm
H4sICD9gdF0CA2lyaXNfdHJhaW4uZXhtAIVWW7LrIAz77ypYQYaHMbD/jV0wYpqCOPcjk04dP5Bl
mRC9E5c++oiLT3X50f6Ozvkn4Gmf/Pj+Z3KpP6H/Xobx/kh/xyc76U94yq/nMKb+O3Tj+G95mWfu
X6eec3j5HvrHKL2g1AsJ3eBnQW/PYRSElV+jImfuT5xhvwWp5QxOzFt+jzI8Uv+Ahs29iGje7fRc
OcWMeQ9bu8F3Q7wdpQGELWcBQqPqoyuKjohVrHtB1eDL1p0NhNK/Tr0gtWaHPazAM52eo2VyB75Y
QdmqJWG/BAt72AVCYmFHH9U8X8Cvo0Q7SjYe6R52GDOqPYCvFnZ1ZmtZQ9jB3cqq9WB83oEv8PTv
cVjGiemEMJ3sG4OUzDPsnrMrl5wVOTMDPhrwYgjV3djQ7MJmJcM4CvM7CBX9HEbZjQGTndlkV5xR
TmOxggbj5ZazoCuNTfYAITLeroLaSTAxz2j8OWiipn0R/cy7vFXoEPEshqk6ZSMoNoJqcko8oxWk
lrOeYjyFWFi1CmoKE6kAJnjGPg8QIivIg32FhfXISQhWMPbKWvaffkbDNluExDaSx3T7/SiKQWps
kAq2g568nfOZ0ezGhDHYlJFBikYTOp/Fwjan1ra6M0EwDunGBHUKbSDz6XlBs5/Cte/L+MQ5NKoV
o+dBkwzQE2f83Ct08wbQpDEQ/rwnZGvVHOCwF1RQbTyrncPbbqopYF9i1JTXVSCyjdRu45AxZcqu
Amo5L9UmMJ5Q80+EFGI8R1AYQhUgUITWCCrThNXstOfML731Z7NnzsKWa0BYYdtBX+eMt5z1vA9N
T/krbOSqWYDQvGYdS6dB+37k7X2UyheA4BJBc85rs9zu1NkGiAK/VFMMJc9atjYSucJ+ETruQ+nO
+BlWb55TMBITjLkiw225JhylMQVbvA23deXvYQeuk9yZCWOGpzKpUezPeA7SVLB4GsXUpN2a/b7y
XOWtrH563Av85x++mk8QoA0AAA==
EOF

cat<<EOF | base64 -d | zcat > iris_unlabeled.exm
H4sICF1GeV0CA2lyaXNfdW5sYWJlbGVkLmV4bQBlVVG27CAI++8quoIeRUDd/8YexNh65330TBkQ
SQK0Srn18kdvecZtj8evXPaU+G13i6c+5dJnhm23xlOfDrs9Nd7tLk+N+B72SF/YLfwatoTdws58
aSvj87513uKJe8LusBUxeuX/Lf7b8Ra5BDET/n1eYVv4R7yXeJfjvsl69OqsL+9JfE5sijs87IF6
DThbxHvYJeKTjwp+lr/Bn3j1D56OfIb89YfPetTTGJ+4Hf6K+gT3GTh04G3g2ohnIJ4YLwP+Av7q
M5i/UB9jPekv0MtX3ay5XYt3Q0w98H3nB88b8QjwKOob5F+IN/Uz2pm3sN5Be+s5iCf7Y/Buhd2R
L/XR43wnvnngEfK/803wqfBnvzn4cvSvEL/xPn39HXX77dRboXdqUegX5HOcH5iHNQvK/E6+lf1Y
yU8hv4X1CPMV8tsZX3h+8dnZL068/+MX1G+Ia5zPwh5Jvpx6TurZOV8O/pf+Rj4m9a7Qd+kp4Gvr
3xE/bwfmwXku7zwvfvxeuI36lzffwq9v/376tJe/zK/gPPEYsbRXnzV/ez9U8jVZz+/+yT5V9sTa
Rys/7mQ/zKO/lfw28q3HvhHqOQ+9jPo6943j/Je/UZ/F9299znlYeivrG6xn17f1dvK3+WgHv4L5
+Pqtcx9Uxivny4/75Tg/sP+WX3/i5e3vzvrWvizcN/L26zd/Tn3nMc/C74Ue3w/D/tl4dn8raixH
v/i777/6El/7o8+K98O/+qmxn9a812MfNN43Wf/mvx7zWv7EZ+1LFzv0SL+z35zzL/z+FfaDYF5k
favIx7nvzn7twP8Pl9soX4YHAAA=
EOF

exit 0