# Check Internet
wget -q --tries=10 --timeout=20 --spider http://google.com
if [[ $? -eq 0 ]]; then
        echo "Internet: True"
		MACHINE_TYPE=`uname -m`
		if [ ${MACHINE_TYPE} == 'x86_64' ]; then
			echo "Architecture: x64"
			wget https://github.com/laferenorg/CppGame/releases/download/v1.1/libSDL2.a
			wget https://github.com/laferenorg/CppGame/releases/download/v1.1/libSDL2_image.a
			https://github.com/laferenorg/CppGame/releases/download/v1.1/SDL2.zip
			unzip SDL2.zip
			mv SDL2 include/
			mv libSDL2.a libs/
			mv libSDL2_image.a libs/
		else
			echo "Architecture: x32"
			wget https://github.com/laferenorg/CppGame/releases/download/v1.0/libSDL2.a
			wget https://github.com/laferenorg/CppGame/releases/download/v1.0/libSDL2_image.a
			https://github.com/laferenorg/CppGame/releases/download/v1.0/SDL2.zip
			unzip SDL2.zip
			mv SDL2 include/
			mv libSDL2.a libs/
			mv libSDL2_image.a libs/
		fi
else
        echo "Internet: False"
fi
