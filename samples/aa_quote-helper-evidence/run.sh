# THIS FILE IS FOR REFERENCE. DO NOT MERGE IT TO MASTER. REMOVE BEFORE MERGING.


docker build -t sagoel/oe-getting-report:0.1 .
docker run --device /dev/sgx:/dev/sgx sagoel/oe-getting-report:0.1 

docker push sagoel/oe-getting-report:0.1

kubectl apply -f check-quote-helper.yaml
kubectl delete job/check-quote-helper

make run 
make