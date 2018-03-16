kinova:
	swig -Wall -modern -python -c++ -Imodded_api -I/usr/local/include -I/usr/include kinova_raw.i
	g++ -fPIC -Wall -Wextra -shared kinova_raw_wrap.cxx -o _kinova_raw.so \
	 -I/usr/local/include -Imodded_api \
	 -I/home/will/anaconda3/include/python3.6m \
	 -Lmodded_api \
	 -L:modded_api/Kinova.API.CommLayerUbuntu.so -l:Kinova.API.CommLayerUbuntu.so \
	 -L:modded_api/Kinova.API.UsbCommandLayerUbuntu.so -l:Kinova.API.USBCommandLayerUbuntu.so \
	 -L:modded_api/Kinova.API.EthCommandLayerUbuntu.so -l:Kinova.API.EthCommandLayerUbuntu.so \
	 -L:modded_api/Kinova.API.EthCommLayerUbuntu.so -l:Kinova.API.EthCommLayerUbuntu.so

 # -I/usr/include/python2.7 -I/usr/include/x86_64-linux-gnu/python2.7 \


example:
	swig -python example.i
	gcc -c -fpic example.c example_wrap.c -I/usr/include/python2.7 -I/usr/include/x86_64-linux-gnu/python2.7
	gcc -shared example.o example_wrap.o -o _example.so

clean:
	-rm *_wrap.c
	-rm *_wrap.cxx
	-rm *.o
	-rm *.so
	-rm example.py
