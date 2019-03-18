echo "Serão instalados pacotes para preparar o ambiente para execução e compilação do projeto. Clique skips e nexts, instale na pasta padrão, selecione todos os componentes 0_0. Finalize a instalação sem rodar o QtCreator. (exatos comandos: next - skip - next - next - marcar qt5.12.0 e next - agree e next - install - desmarcar Launch qtcreator e finish)."
read -r -p "Press any key to continue..." key
sudo apt install qt5-default
sudo apt-get install wget
wget http://download.qt.io/official_releases/qt/5.12/5.12.0/qt-opensource-linux-x64-5.12.0.run
chmod +x qt-opensource-linux-x64-5.12.0.run
./qt-opensource-linux-x64-5.12.0.run
sudo apt-get install build-essential
sudo apt-get install libfontconfig1
sudo apt-get install mesa-common-dev
sudo apt-get install libglu1-mesa-dev -y
echo "Agora iremos compilar e construir o projeto."
read -r -p "Press any key to continue..." key
qmake orbal.pro
make
echo "***Agora podemos executar o arquivo binario na pasta bin. QtCreator irá abrir com o projeto.***"
$HOME/Qt5.12.0/Tools/QtCreator/bin/qtcreator orbal.pro
