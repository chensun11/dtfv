all: lib fv select pca gmm
fv:
	g++ -O2 -o compute_fv compute_fv.cpp fisher.cpp pca.cpp gmm.cpp feature.cpp -lvl -lalg -L./alglib -L./vl
lib:
	g++ -O2 -o alglib/libalg.so alglib/*.cpp -shared -fPIC
select:
	g++ -O2 -o select_pts select_pts.cpp feature.cpp
pca:
	g++ -O2 -o train_pca train_pca.cpp pca.cpp -lalg -L./alglib
gmm:
	g++ -O2 -o train_gmm train_gmm.cpp gmm.cpp -lvl -L./vl
clean:
	rm compute_fv alglib/libalg.so select_pts train_pca train_gmm
