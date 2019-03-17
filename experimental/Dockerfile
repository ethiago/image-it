FROM alpine:3.9

RUN apk add build-base curl python-dev libpng

RUN curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py && \
    python get-pip.py && \
    python -m pip install numpy

COPY --from=image-it /image-it/image-it .

COPY waveGenerator.py .

RUN printf `python waveGenerator.py` | ./image-it
